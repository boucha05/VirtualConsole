local black = 0
local dark_blue = 1
local dark_purple = 2
local dark_green = 3
local brown = 4
local dark_gray = 5
local light_gray = 6
local white = 7
local red = 8
local orange = 9
local yellow = 10
local green = 11
local blue = 12
local indigo = 13
local pink = 14
local peach = 15

local mem_sprite_width = 128
local mem_sprite_height = 128
local mem_sprite_size = mem_sprite_width * mem_sprite_height * 4
local mem_scratch_size = 0x8000

local mem_sprite_addr = 0x0000
local mem_scratch_addr = mem_sprite_addr + mem_sprite_size

local mem_size = mem_scratch_addr + mem_scratch_size

function init()
    memsize(mem_size)

    colorcount(16)
    colortable(black, 0, 0, 0)
    colortable(dark_blue, 29, 43, 83)
    colortable(dark_purple, 126, 37, 83)
    colortable(dark_green, 0, 135, 41)
    colortable(brown, 171, 82, 54)
    colortable(dark_gray, 95, 87, 79)
    colortable(light_gray, 194, 195, 199)
    colortable(white, 255, 241, 232)
    colortable(red, 255, 0, 77)
    colortable(orange, 255, 163, 0)
    colortable(yellow, 255, 255, 39)
    colortable(green, 0, 231, 86)
    colortable(blue, 41, 173, 255)
    colortable(indigo, 131, 118, 156)
    colortable(pink, 255, 119, 168)
    colortable(peach, 255, 204, 170)

    fileload(mem_scratch_addr, "..\\Content\\SpriteSheet.Bitmap")
    bmpload(mem_sprite_addr, mem_sprite_width, 4, 0, mem_scratch_addr, 128, 128)
end

function update()
end

function render()
    color(dark_blue)
    cls()

    camera(10, 10)
    for y = 0, 3 do
        for x = 0, 3 do
            c = y * 4 + x
            color(c)
            rectfill(x * 50, y * 50, 40, 40)

            color(15 - c)
            rect(x * 50, y * 50, 40, 40)
        end
    end

    camera(210, 10)
    sprsheet(mem_sprite_addr, 4, 0, 8, 8, 16, 16)
    spr(0, 0, 0, 16, 16)
end
