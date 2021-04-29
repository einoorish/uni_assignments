var numbers = [1, -2, 9, -5,  4]

console.log(numbers.sort(function(a, b) {
  var A = a
  var B = b
  if (A<0) {
    A=-A
  }
  if (B<0) {
    B=-B
  }

    if(A>B) return 1
    else return -1

}))