# SOMBRA
Simple Objects Minimal Bidimensional RAsterizer (SOMBRA) is a C++ 2D rasterizer able to draw a scene with simple objects and color them. The scene description must be provided in a JSON file with the specific structure designed for SOMBRA features.

## Features
* [X] 2D Primitives (single pixel thickness)
    * [x] Line segment 
    * [X] Circle
    * [X] Circle arcs
    * [X] Polylines
    * [X] Polygons
* [ ] Color-filling algorithms
    * [ ] Scan-line 
    * [X] Flood fill
* [ ] Anti-aliasing algorithms
    * [ ] Xiaolin Wu
    * [X] Simple convolution
* [ ] Extra features
    * [ ] Layers
    * [ ] Groups
    * [X] Color palette
    * [ ] Viewports

## Running SOMBRA

To execute SOMBRA you must have C++17 compiler installed on your machine. An [external library](https://github.com/open-source-parsers/jsoncpp) was used to parse JSON files. The library files are already included in the project. 

Access the project root folder and build the project running:

```bash
    g++ -std=c++17 -I include/ src/*.cpp include/jsoncpp.cpp -o my_executable
```

Then, run the executable passing the scene description file and the name of the output image file as parameters:

```bash
    ./my_executable scene.json img.ppm
```

The scene description must be a .json file, and the output image must be a .ppm file.

## Scene Description

The scene description file uses JSON format with a specific structure to describe the objects and use the features of SOMBRA. The description file must be of the following format

```json
{
  "color_palette": [
    {
      "name": "blue",
      "r": 0,
      "g": 0,
      "b": 255
    },
    {
      "name": "yellowish",
      "r": 255,
      "g": 255,
      "b": 125
    },
    {
      "name": "white",
      "r": 255,
      "g": 255,
      "b": 255
    }
  ],
  "width": 800,
  "height": 800,
  "background_color": {
    "name": "white"
  },
  "anti_alias": "on",
  "objects": [
    {
      "type": "line",
      "start_point": {
        "x": 0,
        "y": 0
      },
      "end_point": {
        "x": 400,
        "y": 400
      },
      "color": {
        "r": 100,
        "g": 100,
        "b": 100
      }
    },
    {
      "type": "circle",
      "center_point": {
        "x": 400,
        "y": 400
      },
      "radius": 75,
      "color": {
        "r": 0,
        "g": 0,
        "b": 0
      }
    },
    {
      "type": "arc",
      "center_point": {
        "x": 500,
        "y": 350
      },
      "start_point": {
        "x": 500,
        "y": 50
      },
      "angle": 180,
      "color": {
        "r": 255,
        "g": 255,
        "b": 0
      }
    },
    {
      "type": "polyline",
      "points": [
        {
          "x": 130,
          "y": 50
        },
        {
          "x": 352,
          "y": 5
        },
        {
          "x": 402,
          "y": 712
        }
      ],
      "color": {
        "r": 145,
        "g": 186,
        "b": 32
      }
    },
    {
      "type": "polygon",
      "points": [
        {
          "x": 156,
          "y": 210
        },
        {
          "x": 30,
          "y": 501
        },
        {
          "x": 352,
          "y": 563
        },
        {
          "x": 402,
          "y": 712
        }
      ],
      "color": {
        "r": 242,
        "g": 89,
        "b": 74
      }
    }
  ],
  "color_fills": [
    {
      "seed": {
        "x": 10,
        "y": 5
      },
      "color": {
        "name": "yellowish"
      }
    },
    {
      "seed": {
        "x": 400,
        "y": 399
      },
      "color": {
        "name": "blue"
      }
    }
  ]
}
```

### color_palette (optional)
Used to name RGB colors so you can refer to them later in the description. It is an array of objects containing the following attributes

* **name**: color nickname
* **r**: red value of RGB color (0-255)
* **g**: red value of RGB color (0-255)
* **b**: red value of RGB color (0-255)

```json
"color_palette": [
    {
      "name": "red",
      "r": 255,
      "g": 0,
      "b": 0
    },
    {
      "name": "green",
      "r": 0,
      "g": 255,
      "b": 0
    },
    {
      "name": "blue",
      "r": 0,
      "g": 0,
      "b": 255
    }
]
```
### width
Width of the canvas. It must be a positive integer number.

### height
Height of the canvas. It must be a positive integer number.

### background_color (optional)
Used to set the canvas background color. It must be a *color object*.

*Color objects* are objects containing either the following RGB attributes

* **r**: red value of RGB color (0-255)
* **g**: red value of RGB color (0-255)
* **b**: red value of RGB color (0-255)

or a single attribute containing a previously defined color name

* **name**: color nickname

```json
"background_color": {
    "r": 0,
    "g": 255,
    "b": 255
}

"background_color": {
    "name": "white" 
}
```

### anti_alias (optional)
Used to apply the anti-alias algorithm after the drawing of all the objects on canvas. It must be set to **on** if the anti-alias technique should be applied.

```json
"anti_alias": "on"
```

### objects (optional)
Array of objects that should be drawn on canvas. Each object is itself a JSON object and must have a **type** attribute indicating which primitive it is describing, along with its peculiar attributes. The possible types are **line**, **circle**, **arc**, **polyline** and **polygon**. Each of these types will be described below.

#### line type
Describe a line on canvas using Bresenham algorithm. It must have a starting point and an ending point positive integer coordinates, along with a *color object*.

```json
{
    "type": "line",
    "start_point": {
        "x": 0,
        "y": 0
    },
    "end_point": {
        "x": 400,
        "y": 400
    },
    "color": {
        "r": 100,
        "g": 100,
        "b": 100
    }
}
```

#### circle type
Describe a circle on canvas. It must have a center point with positive integer coordinates, along with a positive integer radius and a *color object*.

```json
{
    "type": "circle",
    "center_point": {
        "x": 400,
        "y": 400
    },
    "radius": 150,
    "color": {
        "r": 100,
        "g": 100,
        "b": 100
    }
}
```

#### arc type
Describe an arc on canvas. It must have a center point with positive integer coordinates, a starting point for the arc with positive integer coordinates, a positive integer angle and *color object*. The arc angle is drawn counter-clockwise considering the starting point.

```json
{
    "type": "arc",
    "center_point": {
        "x": 500,
        "y": 350
    },
    "start_point": {
        "x": 500,
        "y": 50
    },
    "angle": 180,
    "color": {
        "name": "blue"
    }
}
```

#### polyline type
Describe a polyline on canvas, which is a sequence of points connected. It must have an array of points, each one with positive integer coordinates, and a *color object*.

```json
{
    "type": "polyline",
    "points": [
        {
            "x": 130,
            "y": 50
        },
        {
            "x": 352,
            "y": 5
        },
        {
            "x": 402,
            "y": 712
        }
    ],
    "color": {
        "r": 145,
        "g": 186,
        "b": 32
    }
}
```

#### polygon type
Describe a polygon on canvas, which is a sequence of points connected, with the last point connected to the first one. It must have an array of points, each one with positive integer coordinates, and a *color object*.

```json
{
    "type": "polygon",
    "points": [
        {
            "x": 156,
            "y": 210
        },
        {
            "x": 30,
            "y": 501
        },
        {
            "x": 352,
            "y": 563
        },
        {
            "x": 402,
            "y": 712
        }
    ],
    "color": {
        "r": 242,
        "g": 89,
        "b": 74
    }
}
```

### color_fills (optional)
Describe the color fillings of the scene. It is an array of JSON objects, each one containing a seed point (where the filling must begin) with positive integer coordinates and a *color object*.

```json
"color_fills": [
    {
        "seed": {
            "x": 10,
            "y": 5
        },
        "color": {
            "name": "yellowish"
        }
    },
    {
        "seed": {
            "x": 400,
            "y": 399
        },
        "color": {
            "name": "blue"
        }
    }
]
```