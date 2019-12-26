# sliderz

Qt app to get sliders with min/max/step/unit and a label, from a json
description, that write their index and value, when changed and on start, to the
`stdout`, to quickly add interactivity to another program, especially when
prototyping.

# How to

Write a file called `sliderz.json` in a directory, with a format like this:

```
{
"window title": [
    { "name": "feedback", "default": 30, "min": 0, "max": 125, "step": 1, "unit": "%"},
    { "name": "😍", default": 5000, "min": 100, "max": 20000, "step": 1, "unit": "Hz"}
    { "name": "🏊", default": 0.1, "min": 0.0, "max": 1.0, "step": 0.1, "unit": "☝️"}
  ]
}
```

Then run the `sliderz` executable from this directory, and pipe it to your
program. The format is:

```
x:y\n
```

where `x` is the index of the parameter (starting from 0), and `y` is the new
value of the parameter.

# License

MIT
