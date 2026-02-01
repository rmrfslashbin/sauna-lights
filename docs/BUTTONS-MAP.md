# Complete Button Code Reference

## Usage with PT2262 Component

These tri-state codes are used directly with the custom PT2262 component:

```yaml
button:
  - platform: template
    name: "Red"
    on_press:
      - pt2262.send:
          id: rf_transmitter
          code: "0X00Z1XZ00ZZ"  # Use tri-state code directly
```

**No binary conversion needed** - the PT2262 component handles proper pulse pair encoding automatically.

See `external_components/pt2262/README.md` for component documentation.

## House Code

| Parameter | Value |
|-----------|-------|
| Decimal | 8313 |
| Tri-State | `0X00Z1XZ` |

## Button Mapping

| Cmd | Button | Tri-State Code |
|----:|--------|----------------|
| 1 | Brightness Up | `0X00Z1XZ000Z` |
| 2 | Brightness Down | `0X00Z1XZ000X` |
| 3 | Fast Forward | `0X00Z1XZ0001` |
| 4 | Power | `0X00Z1XZ00Z0` |
| 5 | Red | `0X00Z1XZ00ZZ` |
| 6 | Green | `0X00Z1XZ00ZX` |
| 7 | Blue | `0X00Z1XZ00Z1` |
| 8 | White | `0X00Z1XZ00X0` |
| 9 | R+1 | `0X00Z1XZ00XZ` |
| 10 | G+1 | `0X00Z1XZ00XX` |
| 11 | B+1 | `0X00Z1XZ00X1` |
| 12 | W+1 | `0X00Z1XZ0010` |
| 13 | R+2 | `0X00Z1XZ001Z` |
| 14 | G+2 | `0X00Z1XZ001X` |
| 15 | B+2 | `0X00Z1XZ0011` |
| 16 | W+2 | `0X00Z1XZ0Z00` |
| 17 | R+3 | `0X00Z1XZ0Z0Z` |
| 18 | G+3 | `0X00Z1XZ0Z0X` |
| 19 | B+3 | `0X00Z1XZ0Z01` |
| 20 | W+3 | `0X00Z1XZ0ZZ0` |
| 21 | R+4 | `0X00Z1XZ0ZZZ` |
| 22 | G+4 | `0X00Z1XZ0ZZX` |
| 23 | B+4 | `0X00Z1XZ0ZZ1` |
| 24 | W+4 | `0X00Z1XZ0ZX0` |
| 25 | R-Up | `0X00Z1XZ0ZXZ` |
| 26 | G-Up | `0X00Z1XZ0ZXX` |
| 27 | B-Up | `0X00Z1XZ0ZX1` |
| 28 | Quick | `0X00Z1XZ0Z10` |
| 29 | R-Dn | `0X00Z1XZ0Z1Z` |
| 30 | G-Dn | `0X00Z1XZ0Z1X` |
| 31 | B-Dn | `0X00Z1XZ0Z11` |
| 32 | Slow | `0X00Z1XZ0X00` |
| 33 | DIY1 | `0X00Z1XZ0X0Z` |
| 34 | DIY2 | `0X00Z1XZ0X0X` |
| 35 | DIY3 | `0X00Z1XZ0X01` |
| 36 | Auto | `0X00Z1XZ0XZ0` |
| 37 | DIY4 | `0X00Z1XZ0XZZ` |
| 38 | DIY5 | `0X00Z1XZ0XZX` |
| 39 | DIY6 | `0X00Z1XZ0XZ1` |
| 40 | Flash | `0X00Z1XZ0XX0` |
| 41 | Jump3 | `0X00Z1XZ0XXZ` |
| 42 | Jump7 | `0X00Z1XZ0XXX` |
| 43 | Fade3 | `0X00Z1XZ0XX1` |
| 44 | Fade7 | `0X00Z1XZ0X10` |

*All codes verified via rtl_433 capture.*
