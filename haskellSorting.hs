-- sorting and folds hw

-- 1a
insert :: Ord a => a -> [a] -> [a]
insert x [] = [x]
insert x (y:ys)
  | x <= y = x : y : ys
  | otherwise = y : insert x ys


-- 1b
isort :: Ord a => [a] -> [a]
isort [] = []
isort (x:xs) = insert x (isort xs)


-- 2a
merge :: Ord a => [a] -> [a] -> [a]
merge [] ys = ys
merge xs [] = xs
merge (x:xs) (y:ys)
  | x <= y = x : merge xs (y:ys)
  | otherwise = y : merge (x:xs) ys


-- 2b
halve :: [a] -> ([a], [a])
halve xs = splitAt (length xs `div` 2) xs


-- 2c
msort :: Ord a => [a] -> [a]
msort [] = []
msort [x] = [x]
msort xs = merge (msort left) (msort right)
  where (left, right) = halve xs


-- 3a
myMap :: (a -> b) -> [a] -> [b]
myMap' f = foldr (\x acc -> f x : acc) []


-- 3b
myFilter :: (a -> Bool) -> [a] -> [a]
myFilter p = foldr (\x acc -> if p x then x : acc else acc) []


-- 3c
myFact :: Int -> Int
myFact n = foldr (*) 1 [1..n]


-- 3d
myRevers :: [a] -> [a]
myRevers = foldr (\x acc -> acc ++ [x]) []
