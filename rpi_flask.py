from flask import Flask, request, jsonify
import threading
import time

app = Flask(__name__)

# Dictionary to store distances reported by players
player_distances = {}

# Function to monitor player distances
def monitor_distances():
    while True:
        for player, distance in player_distances.items():
            if distance <= 20:
                print(f"Player {player} is within 20 meters of the flag!")
            else:
                print(f"Player {player} is outside the range.")
        time.sleep(1)  # Check every second

# Flask route to update player distances
@app.route('/update_distance', methods=['POST'])
def update_distance():
    data = request.json
    player_id = data['player_id']
    distance = data['distance']
    
    # Update the player's distance in the dictionary
    player_distances[player_id] = distance
    
    return jsonify({"status": "success", "player_id": player_id, "distance": distance})

# Start Flask server and monitoring in parallel
if __name__ == '__main__':
    # Start the monitoring thread
    monitor_thread = threading.Thread(target=monitor_distances)
    monitor_thread.daemon = True
    monitor_thread.start()

    # Start the Flask app
    app.run(host="0.0.0.0", port=5000)
