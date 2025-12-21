const express = require('express');
const { execFile } = require('child_process');
const cors = require('cors');
const path = require('path');

const app = express();
const port = 3000;

app.use(cors());
app.use(express.json());

app.post('/solve', (req, res) => {
    const encoded_array = req.body.encoded_array;
    
    const args = encoded_array.map(String);

    const solverPath = path.join(__dirname, 'linux_solver');

    execFile(solverPath, args, (err, stdout, stderr) => {
        if (err) {
            return res.status(500).json({
                error: err.message,
                stderr
            });
        }
        res.json({ board: stdout.trim() });
    });
});

app.listen(port, () => console.log(`Listening on port ${port}`));


