class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // Closest point on the rectangle to the circle's center
        int closestX = max(x1, min(xCenter, x2));
        int closestY = max(y1, min(yCenter, y2));

        // Distance from the center to that point
        int dx = xCenter - closestX;
        int dy = yCenter - closestY;

        // Compare squared distances to avoid floating point
        return dx * dx + dy * dy <= radius * radius;
    }
};