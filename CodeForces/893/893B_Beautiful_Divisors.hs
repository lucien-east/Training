
main = do
    n <- readLn :: IO Int
    let ans = solve n
    print ans

solve :: Int -> Int
solve n = maximum . filter (\x -> n `mod` x == 0) $ beauti_num n
    where beauti_num n = takeWhile (<=n) $ map (\k -> 2^(k-1)*(2^k-1)) [1..]

