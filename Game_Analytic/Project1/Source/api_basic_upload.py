import flask #import Flask, request, Blueprint, make_response

api_basic_upload = flask.Blueprint('api_basic_upload', __name__)

@api_basic_upload.route('/upload_data', methods=['POST'])
def post_upload():
 try:
   data = flask.request.get_json()
   print(data)   
   return "{'status': 'success'}"
 except Exception as e:
   print(e)
   resp = flask.make_response(str(e), 500)
   return resp