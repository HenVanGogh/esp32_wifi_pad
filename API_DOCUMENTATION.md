# ESP Controller API Documentation

## Overview
The ESP Controller provides two ways to access input states:
1. REST API endpoint for polling
2. WebSocket connection for real-time updates

## REST API

### Get Input States
Retrieve the current state of all inputs.

**Endpoint:** `GET http://<esp-ip-address>/api/inputs`

**Response Format:** 