import aiofiles
import asyncio

async def main():
    async with aiofiles.open('afile', mode='r') as f:
        async for line in f:
            print(line)

asyncio.run(main())

