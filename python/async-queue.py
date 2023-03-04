import aiofiles
import asyncio
import os

charlist=[0,1,2,3,4,5,6,7,8,9,"a","b","c","d","e","f"]

def chunks(l, n):
    """Yield n number of striped chunks from l."""
    for i in range(0, n):
        yield l[i::n]

async def write_file(dir,filename,size=5):
    # Open a new file to write the list of moves into.
    #await aiofiles.makedir(dir, exist_ok=True)
    async with aiofiles.open(f"{dir}/{filename}", mode='wb') as f:
        await f.write(os.urandom(10))
    return

async def main():

    # A list to be populated with async tasks.
    tasks = []
    outdir="out"
    for a in charlist:
        for b in charlist:
            dir=f"{outdir}/{a}{b}"
            os.makedirs(dir,exist_ok=True)
            for c in range(0,10):
                tasks.append(asyncio.ensure_future(write_file(dir,f"{a}{b}{c}")))

    # Will contain a list of dictionaries containing Pokemons' names and moves
    groups=chunks(tasks,1000)
    for g in groups:
        print(len(g))
        await asyncio.gather(*g)
        print("X",end=None)

asyncio.run(main())
