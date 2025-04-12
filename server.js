const express = require('express');
const path = require('path');
const app = express();

// Serve static files from the 'pages' directory
app.use(express.static(path.join(__dirname, 'pages')));

// Handle root URL
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'pages', 'index.html'));
});

// Use Render's provided PORT
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server is running and accessible at your Render URL`);
});