from flask import Flask
#from flask import redirect
from flask import request
import random
httpRes="0"

from scratchclient import ScratchSession
username = "ccsh_ky"    #Scratch3官網之帳號
password = "123456987"  #Scratch3官網之密碼
projectID = 725470383   #Scratch3官網之專案編號

#和Scratch3官網之專案建立連線
session = ScratchSession(username, password)
connection = session.create_cloud_connection(projectID)

@connection.on("set")
def on_set(variable):
    '''
    scratch3專案執行後，雲端變數一旦改變，
    就會回呼此函式
    variable.name:雲端變數☁ 名稱
    variable.value:雲端變數之值
    '''
    global httpRes
    #將雲端變數之值指定給回應給NodeMCU之變數:httpRes
    httpRes = str(variable.value)
    #print(variable.name,variable.value)
     
app = Flask(__name__)
@app.route("/")
def home():#瀏覽器測試用
    return "<p>Hello, World!</p>"

@app.route("/<value>")
def MiddlewareTransaction(value):
    '''
    一旦接收到NodeMCU傳送的httpRequest後，就會回呼此函式
    ex:NodeMCU傳送 https://192.168.x.x/255
    傳入 value=255
    '''
    global httpRes
    #將雲端變數「A0_R」設定為 value，於scratch3遊戲端可看見數變被改變
    connection.set_cloud_variable('A0_R', int(value))
    return httpRes
#啟動httpServer監聽來自NodeMCU之請求(httpRequest)
app.run(host="0.0.0.0", port=443,ssl_context="adhoc")