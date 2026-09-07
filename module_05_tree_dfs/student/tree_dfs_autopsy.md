# Tree Copy Autopsy

Run the isolated autopsy with a sanitizer. Identify the first invalid memory
access. Then answer:

1. Which function result was ignored?
2. Why was `copy` still `NULL`?
3. Which caller-owned values should a correct failed copy preserve?
4. Where must the error travel through the recursive calls?
