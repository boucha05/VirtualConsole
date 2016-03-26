#The following script was adapted from: https://gist.github.com/jamesgecko/64d7c1fc7d3558ab9902
from PIL import Image
import sys

PALETTE = ((0,0,0), (29, 43, 83), (128, 37, 83), (0, 135, 81),
           (171,82,54), (95,87,79), (194,195,199), (255,241,232),
           (255,0,77), (255,163,0), (255,255,39), (0,231,86),
           (41,173,255), (131,118,156), (255,119,168), (255,204,170))

def main():
    if len(sys.argv) <= 1:
        print "%s filename" % sys.argv[0]
    filename = sys.argv[1]
    im = Image.open(filename)
    px = im.load()
    _, _, width, height = im.getbbox()
    img1 = []
    for y in range(height):
        row1 = []
        for x in range(width):
            pixel1, pixel2 = downsample_2(px[x,y])
            row1.append(pixel1)
        img1.append(row1)
    print_image(img1, width, height)

def print_image(img1, width, height):
    for y in range(height):
        for x in range(width):
            sys.stdout.write(" 0x%02x," %(img1[y][x]))
        sys.stdout.write("\n")

def downsample(rgb):
    ranks = []
    for color in PALETTE:
        ranks.append(score(rgb, color))
    winner = ranks.index(min(ranks))
    return str(hex(winner))[2]

def downsample_2(rgb):
    best_diff = 1000000000
    best_index = None
    runner_up_index = None
    for index, color in enumerate(PALETTE):
        diff = score(rgb, color)
        if diff < best_diff: # lowest difference is closest color
            best_diff = diff
            runner_up_index = best_index
            best_index = index
    return (to_pico_color(best_index), to_pico_color(runner_up_index))

def to_pico_color(color):
    if color == None:
        return 15
    #return str(hex(color))[2]
    return color

def score(rgb1, rgb2):
    return (abs(rgb1[0] - rgb2[0]) +
            abs(rgb1[1] - rgb2[1]) +
            abs(rgb1[2] - rgb2[2]))

if __name__ == '__main__':
    main()
