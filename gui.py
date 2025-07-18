# gui.py
import asyncio
import websockets

async def send_commands():
    uri = "ws://192.168.68.111:8765"  # Replace with your server PC's IP
    async with websockets.connect(uri) as websocket:
        print("Connected to WebSocket server!")
        while True:
            command = input("Enter command (a/b/c/d): ")
            if command in ['a', 'b', 'c', 'd']:
                await websocket.send(command)
                print(f"Sent: {command}")
            else:
                print("Invalid command. Enter only a, b, c, or d.")

if __name__ == "__main__":
    asyncio.run(send_commands())
