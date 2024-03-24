from multiprocessing import connection
from xml.dom.minidom import TypeInfo
from markupsafe import escape
from flask import Flask,render_template,url_for,request,jsonify
import sqlite3
from sqlite3 import Error
# from playsound import playsound



app = Flask(__name__)

"""fix database connection single-time and pass as Parameter !!!!!"""


####################################### INDEX PAGE #########################################
@app.route('/')
def index():
    setShot_Count(20)
    setDuck_Count(0)
    return render_template('index.html')



@app.route('/update_shot',methods=["GET"])
def update_shot():
    if request.method == "GET":


        shot=0
        shot=getShot_Count()
        shot-=1;


        setShot_Count(shot)

        return "Shot updated"


@app.route('/update_duck',methods=["GET"])
def update_duck():
    if request.method == "GET":

        score=0
        score=getDuck_Count()
        score+=100;


        setDuck_Count(score)
        return "Duck updated"

@app.route('/getScore',methods=["GET"])
def getScore():
    if request.method == "GET":

        score=0
        score=getDuck_Count()
        data = {
        'score' : score}

        return jsonify(data)

@app.route('/getShot',methods=["GET"])
def getShot():
    if request.method == "GET":

        shot=0
        shot=getShot_Count()
        data = {
        'shot' : shot}

        return jsonify(data)


@app.route('/getData',methods=["GET"])
def getData():
    if request.method == "GET":

        shot=0
        shot=getShot_Count()
        score=0
        score=getDuck_Count()


        data = {
        'shot' : shot,
        'score' : score

        }

        return jsonify(data)


def getShot_Count():
        conn=create_connection("shot.db")
        cur = conn.cursor()
        cur.execute("SELECT value FROM shot")

        rows = cur.fetchall()

        for row in rows:
            (row)

        conn.close()

        return row[0]

def setShot_Count(duck):
        conn=create_connection("shot.db")
        cur = conn.cursor()
        sql = ''' INSERT or replace INTO shot(id,value)
                VALUES(?,?) '''
        cur = conn.cursor()
        datas=(1,duck)
        cur.execute(sql,datas)
        conn.commit()
        conn.close()




def getDuck_Count():
        conn=create_connection("duck.db")
        cur = conn.cursor()
        cur.execute("SELECT value FROM duck")

        rows = cur.fetchall()

        for row in rows:
            (row)

        conn.close()

        return row[0]

def setDuck_Count(duck):
        conn=create_connection("duck.db")
        cur = conn.cursor()
        sql = ''' INSERT or replace INTO duck(id,value)
                VALUES(?,?) '''
        cur = conn.cursor()
        datas=(1,duck)
        cur.execute(sql,datas)
        conn.commit()
        conn.close()


################ create DB Connection ###################
def create_connection(db_file):

    conn = None
    try:
        conn = sqlite3.connect(db_file)
        return conn
    except Error as e:
        print(e)

    return conn

################### Create tables ##################
def create_table(conn, create_table_sql):
    try:
        c = conn.cursor()
        print("table created")
        c.execute(create_table_sql)
    except Error as e:
        print(e)

