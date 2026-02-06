.PHONY: build run test clean

build:
	go build -o bin/webserver main.go

run:
	go run main.go

test:
	go test -v ./...

clean:
	rm -rf bin/

install:
	go mod download

fmt:
	go fmt ./...

vet:
	go vet ./...
