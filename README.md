![](/screen-shots/natural-scenary.png)
# *`ascii-art-generator`*
`DEMO`

A lightweight tool that uses <a href="https://github.com/lvandeve/lodepng">lodepng</a> to load PNG images and then converts them into ASCII art.

## Requirements
- **Image Format:** Supports PNG files only. If your image is in a different format,

  try using <a href="https://convertio.co/" >Convertio</a> to convert it to PNG.
- **Terminal Emulator:** A 24-bit color supporting terminal:
   - macOs : `iterm`
   - Linux : any terminal
   

## Usage
```
./convert.sh [path to png file]
```
OR
```
./compile.sh
./a.out [png file] > output_file
```

## Example
```
./convert.sh pngs/moon.png
```

![](/screen-shots/moon.png)
