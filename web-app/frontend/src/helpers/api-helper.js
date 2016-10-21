import getRequest from './api-requester';
import urlJoin from 'url-join';
import config from '../configs/api-config';

export function fetchData() {
  return getRequest(getUrl());
}

function getUrl() {
  return urlJoin([config.API_URL, 'posts']);
}