
const path = require('path');
const express = require('express');

const app = express();
const port = process.env.PORT || '8000';

app.get('/', (req, res) => {
  res.status(200).send('Endpoint');
});

app.listen(port, () => {
  console.log(`Listening to requests on http://localhost:${port}`);
});