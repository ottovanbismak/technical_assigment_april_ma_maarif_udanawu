from flask import Flask, request

app = Flask(__name__)

@app.route('/',methods=['POST'])
def data():
    user_data = request.get_json()
    suhu = user_data['suhu']
    kelembapan = user_data['kelembapan']
    nama = user_data['nama']
    return f"haloo dekk {nama}, suhu = {suhu}, kelembapan = {kelembapan}"

if __name__ == '__main__':
    app.run(debug=True,host='0.0.0.0')