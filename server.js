const express = require('express');
const path = require('path');
const { exec } = require('child_process');
const fs = require('fs');

const app = express();

// Serve static files from correct locations
app.use(express.static(path.join(__dirname, 'pages'))); // For HTML files
app.use('/css', express.static(path.join(__dirname, 'pages/css'))); // For CSS

// API endpoints for encryption/decryption
app.post('/run', (req, res) => {
    const { algorithm, key, message } = req.body;
    const cppFile = path.join(__dirname, 'codes', `${algorithm}.cpp`);
    
    fs.writeFileSync('input.txt', `${key}\n${message}`);
    exec(`g++ "${cppFile}" -o "${algorithm}.out" && ./${algorithm}.out`, 
        (error, stdout, stderr) => {
            if (error) return res.status(500).send(stderr);
            res.send(stdout);
        }
    );
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));