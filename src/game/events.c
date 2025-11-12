// # Key/mouse hooks 

#include "../../cub3d.h"

// int handle_close()
// {
//     ft_free_all();
//     return (0);
// }

// int key_press(t_cub *cub, int keycode)
// {
//     if(keycode == KEY_ESC)
//         return (handle_close());
//     cub->game.keys[keycode] = 1;
//     return (0);
// }

// user Input → key_press() → keys[] updated
//                 ↓
//          game_loop() runs every frame
//                 ↓
//          Checks keys[] array
//                 ↓
//          Calls move_player() if needed
//                 ↓
//          Redraws screen

int handle_key(int keycode, t_cub *cub)
{
    if (keycode == KEY_W)
        move_forward(cub);
    else if (keycode == KEY_S)
        move_backward(cub);
    else if (keycode == KEY_A)
        move_left(cub);
    else if (keycode == KEY_D)
        move_right(cub);
    else if (keycode == KEY_LEFT)
        rotate_left(cub);
    else if (keycode == KEY_RIGHT)
        rotate_right(cub);
    else if (keycode == KEY_ESC)
        ft_free_all();
    ray_casting(cub);
    return (0);
}

/*Perfect 😎 — let’s go full visual mode and see how texX and texy actually work together to map your 256×256 texture onto a vertical wall stripe on screen in Cub3D.

🧱 1️⃣ The Texture (256×256)
Here’s your wall texture — think of it as a square image:
Texture image (256x256 pixels)
┌──────────────────────────────────────────────────────────────┐
│                                                              │
│    0,0                    → texX →                    255,0  │
│     ↓                                               ↓         │
│ texY ↓                                              ↓         │
│                                                              │
│                                                              │
│                                                              │
│                                                              │
│    0,255                                            255,255  │
└──────────────────────────────────────────────────────────────┘


🧭 2️⃣ The World Wall (1 tile = 64 units)
Imagine this texture represents one map tile — one wall square.
When your player’s ray hits the wall, it hits somewhere along the face.
That gives you a fractional hit position on the wall — that’s how we find texX.

🎯 3️⃣ Step 1 — Finding texX
Let’s say your ray hit here on the wall’s surface:
Top-down map view (simplified)

    Player
      |
      | Ray hits wall
      ↓
   ┌──────────────┐
   │              │ ← Wall (1 tile wide)
   │    X hit     │
   │              │
   └──────────────┘

The horizontal hit position (wallX) tells you where along the wall (from 0.0 to 1.0) you hit.
You multiply that by the texture width to get texX:
wallX = 0.25  (25% across wall)
texX = wallX * tex->width = 0.25 * 256 = 64

So you’ll use the 64th vertical strip of the texture.

📊 4️⃣ Step 2 — Drawing That Vertical Stripe
Now, on screen, you draw one vertical column of pixels like this:
Screen (vertical column)
↑
│
│   start_y
│   │
│   │  <-- drawing wall pixels here
│   │
│   end_y
│
↓

For every screen pixel j from start_y to end_y,
you compute which row (texy) of that texture stripe to sample.

🧮 5️⃣ Step 3 — Calculating texy
The math:
texy = tex_start + (int)((j - start_y) * ((double)visible_tex_height / wall_height));

This maps the current screen y (j) into a texture y (texy).
Let’s visualize that mapping:
Texture (vertical slice at texX)
┌────────────────────────────────┐
│  texY = 96  ← top visible part │
│                                │
│  texY = 128 ← texture middle   │
│                                │
│  texY = 160 ← bottom visible   │
└────────────────────────────────┘

↓   ↓   ↓   ↓   ↓   ↓   ↓   ↓   ↓   ↓   ↓

Screen column
┌────────────────┐
│ j = start_y    │
│                │
│ j = mid_y      │
│                │
│ j = end_y      │
└────────────────┘

So each pixel on screen (j) corresponds to a pixel row in the texture (texy).

🧩 6️⃣ Step 4 — Combine texX + texy
Now you have both coordinates:
Texture pixel position = (texX, texY)

You use it to sample the color from your texture array:
color = tex->data[texy * tex->width + texX];

That gives you the RGB value for that pixel — which you then draw on the screen.

🧠 7️⃣ Concept Summary
ConceptVariableExplanationHorizontal hit on walltexXFixed for this ray; found from where ray hit wallVertical position on screentexyChanges per pixel; found from j’s position along the drawn wallTexture lookup(texX, texY)Together tell you which exact pixel from texture to drawTexture size256×256Defines the scaling automatically

🧩 8️⃣ Full Visual Flow
TEXTURE 256×256
┌───────────────────────────────┐
│                               │
│        ↑                      │
│        │ texY                 │
│        │                      │
│   texX │ →  │ │ ← vertical stripe (one ray’s slice)
│        │    │ │
│        │    │ │
└────────┼────┼─┴────────────────┘
         ↑    ↑
         │    │
         │    Screen column (i)
         │
         j (looping per pixel)

Each pixel on the screen column samples from one pixel in that vertical stripe of the 256×256 texture.

So:


✅ texX → which column of the texture we’re looking at


✅ texy → which row of that column corresponds to the screen pixel we’re currently drawing


Together → they pick the exact pixel color from the texture.

Would you like me to show you how this changes if your texture is larger than the tile (like 256 vs 64) — i.e. what happens to texY in that case — using a similar diagram?*/