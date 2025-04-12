# Use official Node.js image with g++ pre-installed
FROM node:18-bullseye

# Install dependencies
RUN apt-get update && apt-get install -y g++

# Set working directory
WORKDIR /app

# Copy all files (except those in .dockerignore)
COPY . .

# Install Node.js dependencies
RUN npm install

# Expose the port your app runs on
EXPOSE 3000

# Start command
CMD ["node", "server.js"]