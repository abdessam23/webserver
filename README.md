# Web Server

A simple, lightweight HTTP web server built with Go.

## Features

- 🚀 Fast and efficient HTTP server
- 🔄 RESTful API endpoints
- 📊 JSON response support
- 🏥 Health check endpoint
- 📝 Request logging middleware
- 🎨 Clean and responsive web interface

## Prerequisites

- Go 1.16 or higher

## Installation

Clone the repository:
```bash
git clone https://github.com/abdessam23/webserver.git
cd webserver
```

## Usage

### Using Go Run

```bash
go run main.go
```

### Using Makefile

Build the server:
```bash
make build
```

Run the server:
```bash
make run
```

### Custom Port

Set a custom port using the `PORT` environment variable:
```bash
PORT=3000 go run main.go
```

## API Endpoints

### GET /
Returns the home page with server information and available endpoints.

### GET /api/status
Returns the server status in JSON format.

**Example:**
```bash
curl http://localhost:8080/api/status
```

**Response:**
```json
{
  "message": "Server is running",
  "time": "2026-02-06T07:49:29.146Z"
}
```

### GET /api/time
Returns the current server time.

**Example:**
```bash
curl http://localhost:8080/api/time
```

### POST /api/echo
Echoes back the JSON request body.

**Example:**
```bash
curl -X POST http://localhost:8080/api/echo \
  -H "Content-Type: application/json" \
  -d '{"message": "Hello, World!"}'
```

### GET /health
Health check endpoint for monitoring.

**Example:**
```bash
curl http://localhost:8080/health
```

## Development

### Format Code
```bash
make fmt
```

### Vet Code
```bash
make vet
```

### Clean Build Artifacts
```bash
make clean
```

## Project Structure

```
webserver/
├── main.go         # Main server implementation
├── go.mod          # Go module dependencies
├── Makefile        # Build automation
├── .gitignore      # Git ignore rules
└── README.md       # This file
```

## License

MIT