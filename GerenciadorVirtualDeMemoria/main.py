import sys

files = ''
frames = 256
alg = 'LRU'




def main():
    if len(sys.argv) == 4:
        _, files, frames, alg = sys.argv

        frames = int(frames)

        if alg.upper() == "FIFO":
            pass
    # else:
    #     pass


main()