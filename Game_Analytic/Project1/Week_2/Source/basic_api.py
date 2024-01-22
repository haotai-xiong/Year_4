import flask #import Flask
import api_basic_upload
import flask_cors #import CORS

app = flask.Flask(__name__)
app.secret_key = '_6#y2L"F4Qdkslppwkwn8z\ndkdn\xec]/'
flask_cors.CORS(app)

app.register_blueprint(api_basic_upload.api_basic_upload)

app.run(host='0.0.0.0', debug=True, use_reloader=True)