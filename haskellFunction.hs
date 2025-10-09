-- 1
conditionalAnd :: Bool -> Bool -> Bool
conditionalAnd a b = if a then b else False

guardedAnd :: Bool -> Bool -> Bool
guardedAnd a b | a == True && b == True = True
    | otherwise = False

patternAnd :: Bool -> Bool -> Bool
patternAnd True True = True
patternAnd _ _ = False


-- 2 
logicalOr :: Bool -> Bool -> Bool
logicalOr a b if a then True else b

guardedOr :: Bool -> Bool -> Bool
guardedOr a b | a = True
    | b = True
    | otherwise = False

patternOr :: Bool -> Bool -> Bool
patternOr False False = False
patternOr _ _ = True


-- 3