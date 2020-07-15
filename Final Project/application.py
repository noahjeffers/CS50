import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session

from werkzeug.security import check_password_hash, generate_password_hash


app = Flask(__name__)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
app.config["UPLOAD_FOLDER"] = "/podcasts"
Session(app)

db = SQL("sqlite:///podcast.db")



# INITIAL LOAD OF WEB PAGE
@app.route("/")
@app.route("/index")
def index():
    try:
        attempt = db.execute("SELECT * FROM users")
    except:
        db.execute("CREATE TABLE users("
                            "id INTEGER NOT NULL PRIMARY KEY,"
                            "username TEXT NOT NULL UNIQUE,"
                            "password TEXT NOT NULL,"
                            "description TEXT,"
                            "title VARCHAR2(100),"
                            "creator CHAR(5))")
        db.execute("CREATE TABLE podcasts("
                            "id INTEGER NOT NULL PRIMARY KEY,"
                            "title TEXT NOT NULL,"
                            "creatorID INTEGER NOT NULL,"
                            "description TEXT,"
                            "uploaddate TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
                            "updated TIMESTAMP,"
                            "FOREIGN KEY(creatorID)"
                                "REFERENCES user (id)"
                                "ON DELETE CASCADE)")
        db.execute("CREATE TABLE comments("
                            "id INTEGER NOT NULL PRIMARY KEY,"
                            "name TEXT NOT NULL,"
                            "onpodcast INTEGER NOT NULL,"
                            "content TEXT,"
                            "postdate TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                            "creatorID INTEGER,"
                            "FOREIGN KEY(onpodcast)"
                                "REFERENCES podcast (id)"
                                "ON DELETE CASCADE)")
        db.execute("CREATE TABLE genres("
                            "id INTEGER NOT NULL PRIMARY KEY,"
                            "genre TEXT NOT NULL)")
        db.execute("CREATE TABLE genreobjects("
                            "genreid INTEGER NOT NULL,"
                            "objectid INTEGER,"
                            "FOREIGN KEY(genreid)"
                                "REFERENCES genre (id)"
                                "ON DELETE CASCADE)")
        admin = "admin"
        defaultpassword = "admin"
        if len(attempt)<1:
            db.execute("INSERT INTO users (username, password) VALUES (:username, :password)",
                                    username=admin,
                                    password=generate_password_hash(defaultpassword))

    finally:
        rows = db.execute("SELECT * FROM podcasts LIMIT 5")
        creators = db.execute("SELECT u.id, u.username, (SELECT COUNT(creatorID) FROM podcasts WHERE creatorid =u.id) as num FROM users u WHERE creator = 'TRUE' ORDER BY num DESC LIMIT 3  ")

        return render_template("index.html", rows=rows,creators=creators)


# SORTED INDEX PAGE
@app.route("/<sort>")
def orderedIndex(sort):
    chosenSort = sort
    if chosenSort == "newest":
        rows = db.execute("SELECT * FROM podcasts ORDER BY uploaddate LIMIT 5")
        creators = db.execute("SELECT u.id, u.username, (SELECT COUNT(creatorID) FROM podcasts WHERE creatorid =u.id) as num FROM users u WHERE creator = 'TRUE' ORDER BY num DESC LIMIT 3  ")
        return render_template("index.html", rows=rows,creators=creators)
    elif chosenSort == "oldest":
        rows = db.execute("SELECT * FROM podcasts ORDER BY uploaddate DESC LIMIT 5" )
        creators = db.execute("SELECT u.id, u.username, (SELECT COUNT(creatorID) FROM podcasts WHERE creatorid =u.id) as num FROM users u WHERE creator = 'TRUE' ORDER BY num DESC LIMIT 3  ")
        return render_template("index.html", rows=rows,creators=creators)
    elif chosenSort == "z-a":
        rows = db.execute("SELECT * FROM podcasts ORDER BY title DESC LIMIT 5")
        creators = db.execute("SELECT u.id, u.username, (SELECT COUNT(creatorID) FROM podcasts WHERE creatorid =u.id) as num FROM users u WHERE creator = 'TRUE' ORDER BY num DESC LIMIT 3  ")
        return render_template("index.html", rows=rows,creators=creators)
    elif chosenSort == 'a-z':
        rows = db.execute("SELECT * FROM podcasts LIMIT 5")
        creators = db.execute("SELECT u.id, u.username, (SELECT COUNT(creatorID) FROM podcasts WHERE creatorid =u.id) as num FROM users u WHERE creator = 'TRUE' ORDER BY num DESC LIMIT 3  ")
        return render_template("index.html", rows=rows,creators=creators)
    else:
        return redirect("/")


#LIST OF ALL PODCASTS
@app.route("/podcasts")
def podcasts():
    episodes = db.execute("SELECT * FROM podcasts")
    return render_template("podcasts.html",episodes=episodes)


# LIST OF ALL USERS (CREATORS AND COMMENTERS)
@app.route("/users")
def users():
    accounts = db.execute("SELECT * FROM users WHERE id <> 1")
    return render_template("users.html",accounts=accounts)


# LIST OF GENRES
@app.route("/genres")
def genres():
    return render_template("genres.html")


# REGISTER FOR A NEW ACCOUNT
@app.route("/register",methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if name == "" or password == "" or confirmation == "":
            return render_template("error.html",error="Some of your fields were empty", path= "/register.html", name="Registration")

        else:
            result = db.execute("SELECT username FROM users WHERE username = :username", username=name)
            if len(result) == 0:
                db.execute("INSERT INTO users (username, password, creator) VALUES (:username, :password, :creator)",
                                            username = name,
                                            password = generate_password_hash(password),
                                            creator = "FALSE")
                return render_template("error.html",error="Your account has been created", path= "/", name="Home")
            else:
                return render_template("error.html",error="That username is already taken", path= "/register.html", name="Registration")


# LOG IN
@app.route("/login",methods=["GET", "POST"])
def login():
    if request.method == "GET":
        return render_template("login.html")
    else:
        name = request.form.get("username")
        password = request.form.get("password")

        if name == "" or password == "":
            return render_template("error.html",error="One or both inputs was empty", path= "/login.html", name="Log In")
        else:
            rows = db.execute("SELECT * FROM users WHERE username = :username", username=name)
            if len(rows) != 1 or not check_password_hash(rows[0]["password"], password):
                 return render_template("error.html",error="That username doesn't exist or password is incorrect", path= "/login.html", name="Log In")
            else:
                session["user_id"] = rows[0]["id"]
                return render_template("error.html",error="You are logged in", path= "/", name="Home")

        return render_template("register.html")


# LOG OUT / CLEAR SESSION
@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")

# EDIT USER PROFILE
@app.route("/edit",methods=["GET", "POST"])
def edit():
    if session.get("user_id") is None:
        return redirect("/")
    else:
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users where id = :userid",userid=user_id)
        back="/profile/"+str(user_id)
        if request.method=="GET":

            return render_template("edit.html",user=user)
        else:
            value = request.form.get("submit")
            if value =="submit":
                newtitle = request.form.get("title")
                newdescription = request.form.get("description")
                if db.execute("UPDATE users SET title=:title,description=:description WHERE id=:userid",
                                                            title=newtitle,
                                                            description=newdescription,
                                                            userid=user_id)==None:
                    return render_template("error.html",error="Submission Error, please try again", path="/edit",name="Edit")
                else:
                    return redirect(back)
            else:
                # Passwords
                old = request.form.get("oldpassword")
                new = request.form.get("newpassword")
                confirmation = request.form.get("confirmation")
                if not check_password_hash(user[0]['password'], old):
                    return render_template("error.html",error="Current password doesn't match our information",path="/edit",name="Edit")
                else:
                    if new != confirmation:
                        return render_template("error.html",error="New password does not match confirmation",path=back,name="Edit")
                    else:
                        if db.execute("UPDATE users SET password = :newpassword WHERE id = :userid",
                            newpassword = generate_password_hash(new),
                            userid = user_id) != None:
                            return redirect(back)
                        else:
                            return render_template("error.html",error="The update has failed, please try again",path="/edit",name="Edit")

# PROFILE FOR USER
@app.route("/profile/<userid>")
def profile(userid):

    user = db.execute("SELECT * FROM users WHERE id = :userid", userid = userid)
    comments = db.execute("SELECT * FROM comments WHERE creatorid = :creatorid",creatorid = user[0]['id'])
    if userid == "1":
        return redirect("/admin")
    if user[0]['creator'] == "TRUE":
        podcasts = db.execute("SELECT * FROM podcasts WHERE creatorid = :creatorid",creatorid=user[0]['id'])
        return render_template("profile.html",user=user,comments=comments,podcasts=podcasts)
    else:
        return render_template("profile.html", user=user,comments=comments)

# EPISODE PAGE
@app.route("/episode/<podcastid>")
def episode(podcastid):
    episode=db.execute("SELECT * FROM podcasts where id = :podcastid",podcastid=podcastid)
    creator=db.execute("SELECT * FROM users where id = :creatorid",creatorid=episode[0]['creatorID'])
    comments=db.execute("SELECT * FROM comments where onpodcast = :podcastid",podcastid=episode[0]['id'])
    return render_template("episode.html",episode=episode,creator=creator,comments=comments)


#COMMENT
@app.route("/comment/<podcastid>",methods=["GET", "POST"])
def comment(podcastid):
    commentName = request.form.get("name")
    commentContent = request.form.get("content")
    episodeid=podcastid
    back = "/episode/"+episodeid
    if commentName == "":
        return render_template("error.html",error="You have to enter a name", path=back, name="Episode "+ episodeid)
    elif commentContent =="":
        return render_template("error.html",error="You have to enter a comment", path=back, name="Episode "+ episodeid)

    if session.get("user_id") is None:
        if db.execute("INSERT INTO comments (name, content, onpodcast) VALUES(:name,:content,:onpodcast)",
                                                    name=commentName,
                                                    content=commentContent,
                                                    onpodcast=episodeid) == None:
            return render_template("error.html",error="There was a submission error, please try again", path=back, name="Episode "+ episodeid)
        else:
            return redirect(back)
    else:
        userid = request.form.get("loggedinuser")
        if db.execute("INSERT INTO comments (name, content, onpodcast,creatorid) VALUES(:name,:content,:onpodcast,:creatorid)",
                                                name=commentName,
                                                content=commentContent,
                                                onpodcast=episodeid,
                                                creatorid=userid) == None:
            return render_template("error.html",error="There was a submission error, please try again", path=back, name="Episode "+ episodeid)
        else:
            return redirect(back)
    return redirect(back)


@app.route("/upload", methods = ['GET', 'POST'])
def upload():

    if request.method =="GET":
        return render_template("upload.html")
    else:
        # f = request.files['file']
        # title=request.form.get("title")
        # if f.filename=="":
        #     return redirect("upload.html")
        # filename=f.filename
        # f.save(os.path.join(app.config["UPLOAD_FOLDER"],filename))



        title = request.form.get("title")
        description = request.form.get("description")
        creatorid=request.form.get("loggedinuser")
        back = "/profile/"+creatorid
        uploader = db.execute("SELECT * FROM users WHERE id = :userid",userid=creatorid)
        if uploader[0]['creator'] == "FALSE":
            db.execute("UPDATE users SET creator = 'TRUE' WHERE id = :user_id",user_id=creatorid)

        if db.execute("INSERT INTO podcasts (title, creatorid, description) VALUES (:title, :creatorid, :description)",
                                            title=title,
                                            creatorid=creatorid,
                                            description=description) == None:

            return render_template("error.html",error="There was a submission error, please try again", path="/upload", name="Upload "+ title)
        else:
            return redirect(back)

@app.route("/admin")
def admin():
    admin=db.execute("SELECT * FROM users WHERE id = 1")
    users=db.execute("SELECT * FROM users WHERE id <> 1")
    podcasts=db.execute("SELECT * FROM podcasts")
    comments=db.execute("SELECT * FROM comments")
    return render_template("admin.html",admin=admin,users=users,podcasts=podcasts,comments=comments)

@app.route("/deleteuser/<userid>", methods=["GET", "POST"])
def deleteuser(userid):
    if request.method=="POST":
        db.execute("DELETE FROM users WHERE id = :userid", userid=userid)
        return redirect("/admin")
    else:
        return redirect("/")

@app.route("/deletepodcast/<podcastid>", methods=["GET", "POST"])
def deletepodcast(podcastid):
    if request.method=="POST":
        db.execute("DELETE FROM podcasts WHERE id = :podcastid", podcastid=podcastid)
        return redirect("/admin")
    else:
        return redirect("/")

@app.route("/deletecomment/<commentid>", methods=["GET", "POST"])
def deletecomment(commentid):
    if request.method=="POST":
        back = db.execute("SELECT onpodcast FROM comments WHERE id = :commentid", commentid=commentid)
        pathback="/episode/"+str(back[0]['onpodcast'])
        db.execute("DELETE FROM comments WHERE id = :commentid", commentid=commentid)
        return redirect(pathback)

    else:
        return redirect("/")


