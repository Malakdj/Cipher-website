const express = require("express");
const { exec } = require("child_process");
const fs = require("fs");
const path = require("path");

const app = express();
app.use(express.json());
// app.use(express.static(path.join(__dirname, "pages"))); // Serve HTML pages from 'pages' folder
app.use(express.static(path.join(__dirname))); // Serve from root
const codesDir = path.join(__dirname, "codes"); // Path to C++ files

app.post("/run", (req, res) => {
    const { algorithm, key, message } = req.body;
    console.log("Received algorithm:", algorithm);

    const cppFile = path.join(codesDir, `${algorithm}.cpp`);
    if (!fs.existsSync(cppFile)) {
        return res.status(400).send(`Error: ${algorithm}.cpp not found.`);
    }

    fs.writeFileSync("input.txt", key + "\n" + message);
    const command = `g++ \"${cppFile}\" -o \"${codesDir}/${algorithm}.exe\" && \"${codesDir}/${algorithm}.exe\"`;
    
    exec(command, (error, stdout, stderr) => {
        if (error) {
            res.send("Compilation or Execution Error: " + stderr);
        } else {
            res.send(stdout);
        }
    });
    
});

app.post("/runDecryption", (req, res) => {
    const { algorithm, key, message } = req.body;
    console.log("Received decryption request for algorithm:", algorithm);

    const cppFile = path.join(codesDir, `${algorithm}_decrypt.cpp`);
    if (!fs.existsSync(cppFile)) {
        return res.status(400).send(`Error: ${algorithm}_decrypt.cpp not found.`);
    }

    fs.writeFileSync("input.txt", key + "\n" + message);
    const command = `g++ \"${cppFile}\" -o \"${codesDir}/${algorithm}_decrypt.exe\" && \"${codesDir}/${algorithm}_decrypt.exe\"`;
    
    exec(command, (error, stdout, stderr) => {
        if (error) {
            res.send("Compilation or Execution Error: " + stderr);
        } else {
            res.send(stdout);
        }
    });
});

app.listen(3000, () => {
    console.log("Server running at http://localhost:3000");
});
