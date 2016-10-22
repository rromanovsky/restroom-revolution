import firebase from 'firebase';
import * as actions from '../actions/app';
import config from '../configs/firebase-config';

firebase.initializeApp(config);
const ref = firebase.database().ref('data');



export default function run(dataCallback, errCallback) {
// Get a reference to the storage service, which is used to create references in your storage bucket

  ref.on("child_added", (snapshot) => {
    const message = snapshot.val();

    console.log(message);
    console.group('Firebase adapter');
    console.log('got new message', message);
    console.groupEnd();

    dataCallback(message)
  }, err => {
    errCallback(err);
  });

  ref.on("value", function(snapshot) {


  }, function (errorObject) {
    console.log("The read failed: " + errorObject.code);
  });

  console.group('Firebase adapter runs');
  console.groupEnd();
}



