var arr1=[1, 2, 6, 9];
var arr2= [2, 9];

var arr3 = arr1.filter(function(obj) { return arr2.indexOf(obj) == -1; });

console.log(arr3)