import getRequest from './api-requester';
import config from '../configs/api-config';

export function fetchData() {
  return getRequest(getUrl());
}

function getUrl() {
  return config.API_URL;
}