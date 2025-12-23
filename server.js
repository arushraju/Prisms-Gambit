const express = require('express');
const { execFile } = require('child_process');
const cors = require('cors');
const path = require('path');

const app = express();
const port = process.env.PORT || 3000;

app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, "public")));

app.post("/solve", (req, res) => {
    try {
        const { encoded_array } = req.body;

        if (!Array.isArray(encoded_array)) {
            return res.status(400).json({
                error: "encoded_array must be an array"
            });
        }

        const args = encoded_array.map(String);

        const solverPath = path.join(
            __dirname,
            process.env.SOLVER_PATH || "linux_server"
        );

        execFile(solverPath, args, (err, stdout, stderr) => {
            if (err) {
                console.error("SOLVER ERROR:", err);
                console.error("STDERR:", stderr);
                return res.status(500).json({
                    error: err.message,
                    stderr
                });
            }

            res.json({ board: stdout.trim() });
        });
    } catch (err) {
        console.error("SERVER ERROR:", err);
        res.status(500).json({ error: err.message });
    }
});

app.listen(port, () => console.log(`Listening on port ${port}`));



