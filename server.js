const express = require('express');
const path = require('path');
const { exec } = require('child_process');
const fs = require('fs');
const app = express();

// Middleware
app.use(express.json());
app.use(express.static(path.join(__dirname, 'pages')));
app.use('/css', express.static(path.join(__dirname, 'pages/css')));


// Verify g++ is installed during startup
exec('g++ --version', (error) => {
  if (error) {
    console.error('ERROR: g++ compiler not found. Encryption/decryption will fail.');
  } else {
    console.log('g++ compiler is available');
  }
});
// Handle encryption requests (from runCipher())
app.post('/run', (req, res) => {
    const { algorithm, key, message } = req.body;
    
    // 1. Validate input
    if (!algorithm || !key || !message) {
        return res.status(400).send("Missing required fields");
    }

    // 2. Prepare input file
    fs.writeFileSync('input.txt', `${key}\n${message}`, 'utf8');

    // 3. Execute C++ code
    exec(`g++ codes/${algorithm}.cpp -o ${algorithm}.out && ./${algorithm}.out`, 
        { timeout: 5000 }, // 5-second timeout
        (error, stdout, stderr) => {
            if (error) {
                console.error(`Execution error: ${stderr}`);
                return res.status(500).send(stderr || "Encryption failed");
            }
            res.send(stdout);
        }
    );
});

// Handle decryption requests (from runDecryption())
app.post('/runDecryption', (req, res) => {
    const { algorithm, key, message } = req.body;
    
    // 1. Validate input
    if (!algorithm || !key || !message) {
        return res.status(400).send("Missing required fields");
    }

    // 2. Prepare input file
    fs.writeFileSync('input.txt', `${key}\n${message}`, 'utf8');

    // 3. Execute C++ code
    exec(`g++ codes/${algorithm}_decrypt.cpp -o ${algorithm}_decrypt.out && ./${algorithm}_decrypt.out`, 
        { timeout: 5000 }, // 5-second timeout
        (error, stdout, stderr) => {
            if (error) {
                console.error(`Execution error: ${stderr}`);
                return res.status(500).send(stderr || "Decryption failed");
            }
            res.send(stdout);
        }
    );
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send('Server error');
});

// Start server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server ready at ${PORT}`);
});