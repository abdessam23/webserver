package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"time"
)

type Server struct {
	port string
}

type Response struct {
	Message string    `json:"message"`
	Time    time.Time `json:"time"`
}

func NewServer(port string) *Server {
	return &Server{
		port: port,
	}
}

func (s *Server) homeHandler(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path != "/" {
		http.NotFound(w, r)
		return
	}

	html := `
<!DOCTYPE html>
<html>
<head>
    <title>Web Server</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 50px auto;
            padding: 20px;
            background-color: #f5f5f5;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        h1 {
            color: #333;
        }
        .endpoint {
            background-color: #f9f9f9;
            padding: 10px;
            margin: 10px 0;
            border-left: 4px solid #007bff;
        }
        code {
            background-color: #e9ecef;
            padding: 2px 6px;
            border-radius: 3px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Welcome to the Web Server!</h1>
        <p>This is a simple web server built with Go.</p>
        
        <h2>Available Endpoints:</h2>
        <div class="endpoint">
            <strong>GET /</strong> - This home page
        </div>
        <div class="endpoint">
            <strong>GET /api/status</strong> - Server status in JSON format
        </div>
        <div class="endpoint">
            <strong>GET /api/time</strong> - Current server time
        </div>
        <div class="endpoint">
            <strong>POST /api/echo</strong> - Echo back your JSON request
        </div>
        <div class="endpoint">
            <strong>GET /health</strong> - Health check endpoint
        </div>
        
        <h2>Example Usage:</h2>
        <p>Try: <code>curl http://localhost:` + s.port + `/api/status</code></p>
    </div>
</body>
</html>
`
	w.Header().Set("Content-Type", "text/html")
	fmt.Fprint(w, html)
}

func (s *Server) statusHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}

	response := Response{
		Message: "Server is running",
		Time:    time.Now(),
	}

	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)
}

func (s *Server) timeHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodGet {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}

	response := Response{
		Message: time.Now().Format(time.RFC3339),
		Time:    time.Now(),
	}

	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(response)
}

func (s *Server) echoHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}

	var data map[string]interface{}
	if err := json.NewDecoder(r.Body).Decode(&data); err != nil {
		http.Error(w, "Invalid JSON", http.StatusBadRequest)
		return
	}

	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(data)
}

func (s *Server) healthHandler(w http.ResponseWriter, r *http.Request) {
	w.WriteHeader(http.StatusOK)
	fmt.Fprint(w, "OK")
}

func (s *Server) loggingMiddleware(next http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		start := time.Now()
		log.Printf("%s %s - Started", r.Method, r.URL.Path)
		next(w, r)
		log.Printf("%s %s - Completed in %v", r.Method, r.URL.Path, time.Since(start))
	}
}

func (s *Server) Start() error {
	mux := http.NewServeMux()

	// Register routes
	mux.HandleFunc("/", s.loggingMiddleware(s.homeHandler))
	mux.HandleFunc("/api/status", s.loggingMiddleware(s.statusHandler))
	mux.HandleFunc("/api/time", s.loggingMiddleware(s.timeHandler))
	mux.HandleFunc("/api/echo", s.loggingMiddleware(s.echoHandler))
	mux.HandleFunc("/health", s.healthHandler)

	addr := ":" + s.port
	log.Printf("Starting server on http://localhost%s", addr)

	return http.ListenAndServe(addr, mux)
}

func main() {
	port := os.Getenv("PORT")
	if port == "" {
		port = "8080"
	}

	server := NewServer(port)

	log.Fatal(server.Start())
}
