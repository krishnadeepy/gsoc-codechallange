from flask import Flask, Response, request, render_template, redirect
import os
from werkzeug.utils import secure_filename

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == "__main__":

    app.run(debug=True)

