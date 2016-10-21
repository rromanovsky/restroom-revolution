import _ from 'lodash';


export default function getRequest(url, options = {cache: 'default'}) {
  return makeRequest(url, options)
}

function makeRequest(url, options) {
  return fetch(url, options)
    .then(logResponse.bind(null, options))
    .then(checkResponseStatus)
    .then(getJson)
    .then(consoleLog)
    .catch(errorHandler)
    ;
}

function checkResponseStatus(response) {
  //if (response.status !== 200) {
  //  alert("Something went wrong. Please try again.");
  //}
  return response;
}

function getJson(response) {
  return response.json();
}

function consoleLog(data) {
  console.group('fetch data');
  console.log('data', data);
  console.groupEnd();

  return data;
}

function logResponse(options, response) {
  console.log('...response for', response.url,
    "\r\n", 'status', response.status, response.statusText, response.ok,
    "\r\n", 'options', options,
    "\r\n", 'response', response, "\r\n"
  );

  return response;
}

function errorHandler(err) {
  console.error(err.message);
  console.log(err);
  console.log(err.stack)
}