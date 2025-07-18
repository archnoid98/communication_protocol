# server.py
import asyncio
import websockets
import logging

logging.basicConfig(level=logging.INFO)

clients = set()

async def handler(websocket):
    clients.add(websocket)
    logging.info(f"New client connected: {websocket.remote_address}")
    try:
        async for message in websocket:
            logging.info(f"Received: {message}")
            # Broadcast to all connected clients except sender
            for client in clients:
                if client != websocket:
                    await client.send(message)
    except websockets.exceptions.ConnectionClosed:
        logging.info(f"Client {websocket.remote_address} disconnected")
    finally:
        clients.remove(websocket)

async def main():
    async with websockets.serve(handler, "0.0.0.0", 8765):
        logging.info("WebSocket Server Running on ws://192.168.68.111:8765")
        await asyncio.Future()  # Run forever

if __name__ == "__main__":
    asyncio.run(main())
