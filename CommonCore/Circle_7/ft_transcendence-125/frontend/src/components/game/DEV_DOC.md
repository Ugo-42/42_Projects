# GameApi - Developer Documentation

---

## Players

### `spawnPlayer()`

Creates a player at a grid cell using the specified character.

```ts
api.spawnPlayer(id, characterKey, col, row);
```

**Parameters:**

* `id`: Unique player ID.
* `characterKey`: Character identifier used by `PlayerView`.
* `col`: Grid column.
* `row`: Grid row.

**Example:**

```ts
api.spawnPlayer('p1', 'bbm-player-red', 3, 2);
```

The grid coordinates are converted internally to world coordinates.

---

### `movePlayer()`

Moves an existing player to a grid cell.

```ts
api.movePlayer(id, col, row);
```

**Parameters:**

* `id`: Player ID.
* `col`: Target grid column.
* `row`: Target grid row.

**Example:**

```ts
api.movePlayer('p1', 4, 2);
```

The grid coordinates are converted internally to world coordinates.

---

### `removePlayer()`

Destroys and removes a player.

```ts
api.removePlayer(id);
```

**Example:**

```ts
api.removePlayer('p1');
```

---

## Walls

### `syncWalls()`

Synchronizes rendered walls with the provided wall list. Creates new walls and removes walls that are no longer present.

```ts
api.syncWalls(walls);
```

**Example:**

```ts
api.syncWalls([
    { id: 'w1', col: 4, row: 2 },
    { id: 'w2', col: 5, row: 2 },
]);
```

---

### `breakWall()`

Plays the wall destruction animation. Optionally calls a callback when the animation finishes.

```ts
api.breakWall(id, onComplete?);
```

**Example:**

```ts
api.breakWall('w1', () => {
    console.log('Wall destroyed');
});
```

---

### `hasWallAt()`

Checks whether a wall exists at a grid cell.

Returns the wall ID or `null`.

```ts
const id = api.hasWallAt(col, row);
```

**Example:**

```ts
const wallId = api.hasWallAt(4, 2);

if (wallId) {
    console.log('Wall:', wallId);
}
```

---

## Items

### `syncItems()`

Synchronizes rendered items with the provided item list.

```ts
api.syncItems(items);
```

**Example:**

```ts
api.syncItems([
    {
        id: 'i1',
        type: 'bomb-up',
        col: 3,
        row: 2,
    },
]);
```

---

### `removeItem()`

Destroys and removes an item.

```ts
api.removeItem(id);
```

**Example:**

```ts
api.removeItem('i1');
```

---

## Bombs

### `placeBomb()`

Creates a bomb at a grid cell. Optionally calls a callback when the bomb's visual lifecycle finishes.

```ts
api.placeBomb(id, col, row, onComplete?);
```

**Example:**

```ts
api.placeBomb('b1', 5, 4, () => {
    console.log('Bomb finished');
});
```

---

### `removeBomb()`

Destroys and removes a bomb immediately.

```ts
api.removeBomb(id);
```

**Example:**

```ts
api.removeBomb('b1');
```

---

## Explosions

### `triggerExplosion()`

Triggers an explosion at a grid cell, animates the affected cells, and breaks the specified walls.

```ts
api.triggerExplosion(
    centerCol,
    centerRow,
    hitCells,
    destroyedWallIds,
    onComplete?,
);
```

**Example:**

```ts
api.triggerExplosion(
    5,
    4,
    hitCells,
    ['w1', 'w2'],
    () => {
        console.log('Explosion finished');
    },
);
```

---

## Quick Reference

| Function             | Description                            |
| -------------------- | -------------------------------------- |
| `spawnPlayer()`      | Create player at grid position         |
| `movePlayer()`       | Move player to grid position           |
| `removePlayer()`     | Remove player                          |
| `syncWalls()`        | Synchronize wall views                 |
| `breakWall()`        | Animate wall destruction               |
| `hasWallAt()`        | Get wall ID at grid cell               |
| `syncItems()`        | Synchronize item views                 |
| `removeItem()`       | Remove item                            |
| `placeBomb()`        | Create bomb at grid position           |
| `removeBomb()`       | Remove bomb                            |
| `triggerExplosion()` | Trigger explosion and wall destruction |

