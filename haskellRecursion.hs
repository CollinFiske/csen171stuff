-- 1. a
safetail_conditional :: [a] -> [a]
safetail_conditional xs = if null xs then [] else tail xs

-- 1. b
safetailguarded :: [a] -> [a]
safetailguarded xs | null xs   = []
    | otherwise = tail xs

-- 1. c
safetailpattern :: [a] -> [a]
safetailpattern [] = []
safetailpattern (_:xs) = xs


-- 2
perfects :: Int -> [Int]
perfects n = [x | x <- [1..n], isPerfect x]
    where
        isPerfect num = sum (factors num) == num
        factors num = [f | f <- [1..num-1], num `mod` f == 0]


-- 3. a. 
myand :: [Bool] -> Bool
myand [] = True
myand (x:xs) = x && myand xs 

-- 3. b.
myconcatonate :: [[a]] -> [a]
myconcatonate [] = []
myconcatonate (x:xs) = x ++ myconcatonate xs  

-- 3. c.
myreplicate :: Int -> a -> [a]
myreplicate 0 _ = []
myreplicate m x = x : myreplicate (m-1) x  

-- 3. d.
myindex :: [a] -> Int -> a
(x:_) myindex 0 = x
(_:xs) myindex k = xs myindex (k-1)   
[] myindex _ = error "Index not in list bounds, try again."

-- 3. d.
myelem :: Eq a => a -> [a] -> Bool
myelem _ [] = False
myelem y (x:xs) = (y == x) || myelem y xs  