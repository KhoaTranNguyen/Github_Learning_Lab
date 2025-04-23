from flask import Flask, request

app = Flask(__name__)

@app.route('/gps', methods=['GET'])
def gps_get():
    data = {
        "latitude": request.args.get('lat'),
        "longitude": request.args.get('longitude'),  # changed 'lon' to 'longitude'
        "altitude": request.args.get('alt'),
        "speed": request.args.get('s'),  # speed is sent as 's'
        "time": request.args.get('time')
    }
    print("📡 GPS GET Data Received:", data)
    return "OK"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)