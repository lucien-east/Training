import Control.Monad

main = do
    n <- readLn :: IO Int
    winner <- replicateM n readLn :: IO [Int]
    let ans = simulate winner
    if ans == True
        then putStrLn "YES"
        else putStrLn "NO"
        
simulate :: [Int] -> Bool
simulate = game 1 2 3
    where
        game _ _ _ [] = True
        game play_1 play_2 spec (x:xs)
            | x == play_1   = game play_1 spec play_2 xs
            | x == play_2   = game spec play_2 play_1 xs
            | otherwise = False

