from flask import Flask, request

app = Flask(__name__)

@app.route('/update_distance', methods=['POST'])
def update_distance():
    data = request.json
    player_id = data['player_id']
    distance = data['distance']
    # Process distance and game logic
    return {"status": "success"}

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
