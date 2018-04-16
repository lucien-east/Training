data Direction = MyLeft | MyRight | MyStraight deriving (Show, Eq)
data Point = Point Float Float deriving (Show)

-- Path: (x1,y1) -> (x2,y2) -> (x3, y3)
orientation :: Point -> Point -> Point -> Direction
orientation (Point x1 y1) (Point x2 y2) (Point x3 y3)
    | cross_product < 0 = MyLeft
    | cross_product > 0 = MyRight
    | otherwise         = MyStraight
    where cross_product = (x3-x1)*(y2-y1)-(x2-x1)*(y3-y1)

orientation_list :: [Point] -> [Direction]
orientation_list [] = []
orientation_list (_:[]) = []
orientation_list (_:_:[]) = []
orientation_list (a:b:c:xs) = orientation a b c : orientation_list (b:c:xs)

-- counting distance difference
dist_diff :: Point -> Point -> Float
dist_diff (Point xa ya) (Point xb yb) = (xb*xb+yb*yb)-(xa*xa+ya*ya)

-- angle compare function (if the angle is the same, compare distance)
angle_compare :: Point -> Point -> Float
angle_compare a b
    | direct == MyLeft      = 1                     -- a < b
    | direct == MyRight     = (-1)                  -- a > b
    | direct == MyStraight  = dist_diff a b
    where direct = orientation (Point 0 0) a b

-- sorting angle used polar angle sorting
angle_sort :: [Point] -> [Point]
angle_sort [] = []
angle_sort (p:ps) = 
    let smaller = angle_sort [a | a <- ps, angle_compare p a < 0]
        bigger = angle_sort [a | a <- ps, angle_compare p a >= 0]
    in smaller ++ [p] ++ bigger

-- point shift
point_shift :: Point -> Point -> Point
point_shift (Point xa ya) (Point xb yb) = (Point (xa+xb) (ya+yb))


-- polar angle sorting
polar_angle_sort :: Point -> [Point] -> [Point]
polar_angle_sort (Point x0 y0) points = shift $ angle_sort upper_half ++ angle_sort lower_half
    where upper_half = [ (Point (x-x0) (y-y0)) | (Point x y) <- points, y-y0 >= 0] 
          lower_half = [ (Point (x-x0) (y-y0)) | (Point x y) <- points, y-y0 < 0]
          shift = map (\x -> point_shift (Point x0 y0) x)

-- left lower most points
left_lower_most :: [Point] -> Point
left_lower_most [] = error "empty list"
left_lower_most (a:[]) = a
left_lower_most ((Point xa ya):(Point xb yb):ps)
    | ya < yb = left_lower_most ((Point xa ya):ps)
    | ya > yb = left_lower_most ((Point xb yb):ps)
    | (ya == yb) && (xa < xb)  = left_lower_most ((Point xa ya):ps)
    | (ya == yb) && (xa >= xb) = left_lower_most ((Point xb yb):ps)

-- stack push
stack_push :: Point -> [Point] -> [Point]
stack_push p [] = [p]
stack_push p ps = (p:ps)

-- stack pop
stack_pop :: [Point] -> [Point]
stack_pop [] = []
stack_pop (p:ps) = ps

-- stack top
stack_top :: [Point] -> Point
stack_top [] = error "empty stack"
stack_top (p:_) = p

-- stack next top
stack_next_top :: [Point] -> Point
stack_next_top points = stack_top $ stack_pop points

-- convex scan
convex_scan :: [Point] -> [Point] -> [Point]
convex_scan [] stack = stack
convex_scan (p:ps) stack
    | direct == MyLeft = convex_scan ps (stack_push p stack)
    | otherwise        = convex_scan ps (stack_push p (stack_pop stack))
    where top = stack_top stack
          next_top = stack_next_top stack
          direct = orientation next_top top p

-- Graham's scan
graham_scan :: [Point] -> [Point]
graham_scan [] = []
-- reverse: make the point order be counter-clockwise
graham_scan (a:b:points) = reverse $ convex_scan points stack
    where base = left_lower_most (a:b:points)
          sorted_points = polar_angle_sort base (a:b:points)
          stack = (stack_push b (stack_push a []))


