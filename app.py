from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/sensor', methods=['POST'])
def receive_sensor_data():
    data = request.json
    temperature = data.get('temperature')
    
    print(f"Received temperature: {temperature}°C")
    
    response = {"status": "success", "message": f"Received temperature: {temperature}°C"}
    return jsonify(response), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
