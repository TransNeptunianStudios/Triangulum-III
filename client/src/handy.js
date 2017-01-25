export default class Handy {
  static equalJson(a, b) {
    function check(a, b) {
      for (var attr in a) {
        if (a.hasOwnProperty(attr) && b.hasOwnProperty(attr)) {
          if (a[attr] != b[attr]) {
            switch (a[attr].constructor) {
              case Object:
                return equal(a[attr], b[attr]);
              case Function:
                if (a[attr].toString() != b[attr].toString()) {
                  return false;
                }
                break;
              default:
                return false;
            }
          }
        } else {
          return false;
        }
      }
      return true;
    };
    return check(a, b) && check(b, a);
  }

  static getbitMask(listOfBool) {
    var inputString = "";
    for (var i in listOfBool)
      inputString += listOfBool[i] ? "1" : "0";

    return parseInt(inputString, 2);
  }
}