import requests
def test_post_data():
   url = 'http://localhost:5000/upload_data'
   payload = {"completion_time": 2000,
              "level": 7
              }
   r = requests.post(url, json=payload)
   print(r)

test_post_data()