const express = require('express');
const path = require('path');
const { exec } = require('child_process');
const fs = require('fs');
const app = express();

app.use(express.json());
app.use(express.static(path.join(__dirname, 'pages')));
app.use('/css', express.static(path.join(__dirname, 'pages/css')));

// Check for g++ on startup
exec('g++ --version', (error) => {
  if (error) {
    console.error('ERROR: g++ compiler not found. C++ programs will not run.');
  } else {
    console.log('g++ compiler is available.');
  }
});

// Utility to run a C++ program safely
const runCppProgram = (cppFilePath, outputBinary, callback) => {
  const command = `g++ ${cppFilePath} -o ${outputBinary} && ./${outputBinary}`;
  exec(command, { timeout: 5000 }, callback);
};

// Handle Alberti Cipher (unique inputs)
const handleAlbertiOperation = (req, res, isEncrypt) => {
  const { key, message, rotateInterval } = req.body;

  if (!key || !message || !rotateInterval) {
    return res.status(400).send("Missing key, message or rotation interval");
  }
  if (!/^[A-Za-z]$/.test(key)) {
    return res.status(400).send("Key must be a single letter (A-Z)");
  }
  if (isNaN(rotateInterval) || rotateInterval < 1) {
    return res.status(400).send("Rotation interval must be a positive number");
  }

  const inputContent = `${key}\n${rotateInterval}\n${message}`;
  const operation = isEncrypt ? "encrypt" : "decrypt";
  const filePrefix = `alberti_${operation}`;
  const cppPath = `codes/${filePrefix}.cpp`;

  fs.writeFileSync(`input_${filePrefix}.txt`, inputContent, 'utf8');

  runCppProgram(cppPath, `${filePrefix}.out`, (err, stdout, stderr) => {
    if (err) {
      console.error(`[Alberti ${operation}] Error:`, stderr);
      return res.status(500).send(stderr || `${operation} failed`);
    }
    res.send(stdout);
  });
};

// Generic handler for other ciphers
const handleGenericCipher = (req, res, isEncrypt) => {
  const { algorithm, key, message } = req.body;

  if (!algorithm || !key || !message) {
      return res.status(400).send("Missing algorithm, key, or message");
  }

  // Special handling for Vigenère file names
  let cppFile;
  if (algorithm.toLowerCase() === "vigenère") {
      cppFile = isEncrypt ? "codes/vigenère_encrypt.cpp" : "codes/vigenère_decrypt.cpp";
  } else {
      const operation = isEncrypt ? '' : '_decrypt';
      cppFile = `codes/${algorithm}${operation}.cpp`;
  }

  const inputFile = `input_${algorithm}${isEncrypt ? '' : '_decrypt'}.txt`;
  const outputBinary = `${algorithm}${isEncrypt ? '' : '_decrypt'}.out`;

  fs.writeFileSync(inputFile, `${key}\n${message}`, 'utf8');

  runCppProgram(cppFile, outputBinary, (err, stdout, stderr) => {
      if (err) {
          console.error(`[${algorithm}] Error:`, stderr);
          return res.status(500).send(stderr || `${algorithm} ${isEncrypt ? 'encryption' : 'decryption'} failed`);
      }
      res.send(stdout.trim());
  });
};
// Encryption Route
app.post('/run', (req, res) => {
  const { algorithm } = req.body;
  if (algorithm === 'Alberti') {
    return handleAlbertiOperation(req, res, true);
  }
  handleGenericCipher(req, res, true);
});

// Decryption Route
// Decryption Route
app.post('/runDecryption', (req, res) => {
  const { algorithm } = req.body;
  
  if (algorithm === 'Alberti') {
      return handleAlbertiOperation(req, res, false);
  }
  
  // Special validation for Vigenère
  if (algorithm === 'Vigenère') {
      const { key } = req.body;
      if (!/^[a-zA-Z]+$/.test(key)) {
          return res.status(400).send("Vigenère key must contain only letters");
      }
  }
  
  handleGenericCipher(req, res, false);
});

// Error Middleware
app.use((err, req, res, next) => {
  console.error('Unhandled error:', err.stack);
  res.status(500).send('Server error');
});

// Start Server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`🔐 Cipher server running on port ${PORT}`);
});
