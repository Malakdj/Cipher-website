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

// Handle Alberti Cipher specifically
const handleAlbertiOperation = (req, res, isEncrypt) => {
  const { algorithm, key, message, rotateInterval } = req.body;
  
  // 1. Validate input
  if (!algorithm || !key || !message || !rotateInterval) {
    return res.status(400).send("Missing required fields (key, message, rotationInterval)");
  }

  // Validate key is A-Z single character
  if (!/^[A-Za-z]$/.test(key)) {
    return res.status(400).send("Key must be a single letter A-Z");
  }

  // Validate rotation interval
  if (isNaN(rotateInterval) || rotateInterval < 1) {
    return res.status(400).send("Rotation interval must be a positive number");
  }

  // 2. Prepare input file (format: key\nrotateInterval\nmessage)
  fs.writeFileSync('input.txt', `${key}\n${rotateInterval}\n${message}`, 'utf8');

  // 3. Determine operation type
  const operation = isEncrypt ? 'encrypt' : 'decrypt';
  const cppFile = `codes/alberti_${operation}.cpp`;
  const outputFile = `alberti_${operation}.out`;

  // 4. Execute C++ code
  exec(`g++ ${cppFile} -o ${outputFile} && ./${outputFile}`,
    { timeout: 5000 },
    (error, stdout, stderr) => {
      if (error) {
        console.error(`Alberti ${operation} error:`, {
          error: error.message,
          stderr,
          stdout
        });
        return res.status(500).send(stderr || `${operation} failed`);
      }
      res.send(stdout);
    }
  );
};

// Handle encryption requests
app.post('/run', (req, res) => {
  if (req.body.algorithm === 'Alberti') {
    return handleAlbertiOperation(req, res, true);
  }

  // Original generic handler for other ciphers
  const { algorithm, key, message } = req.body;
  
  if (!algorithm || !key || !message) {
    return res.status(400).send("Missing required fields");
  }

  fs.writeFileSync('input.txt', `${key}\n${message}`, 'utf8');

  exec(`g++ codes/${algorithm}.cpp -o ${algorithm}.out && ./${algorithm}.out`, 
    { timeout: 5000 },
    (error, stdout, stderr) => {
      if (error) {
        console.error(`Execution error: ${stderr}`);
        return res.status(500).send(stderr || "Encryption failed");
      }
      res.send(stdout);
    }
  );
});

// Handle decryption requests
app.post('/runDecryption', (req, res) => {
  if (req.body.algorithm === 'Alberti') {
    return handleAlbertiOperation(req, res, false);
  }

  // Original generic handler for other ciphers
  const { algorithm, key, message } = req.body;
  
  if (!algorithm || !key || !message) {
    return res.status(400).send("Missing required fields");
  }

  fs.writeFileSync('input.txt', `${key}\n${message}`, 'utf8');

  exec(`g++ codes/${algorithm}_decrypt.cpp -o ${algorithm}_decrypt.out && ./${algorithm}_decrypt.out`, 
    { timeout: 5000 },
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
  console.error('Server error:', err.stack);
  res.status(500).send('Server error');
});

// Start server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});