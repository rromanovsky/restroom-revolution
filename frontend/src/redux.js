import _ from 'lodash';
import { combineReducers } from 'redux';
import { createAction, handleAction } from 'redux-actions';

// Actions
export const setNotifications = createAction('NOTIFICATIONS/SET');
export const setRoom = createAction('ROOMS/SET');

// Selectors
export const getNotifications = _.property('notifications');
export const getFloors = _.property('floors');

// Reducers
const notifications = handleAction(setNotifications, (state, { payload }) => payload, false);
const mockup = { doors: [{ status: 0 }, { status: 0 }] }; // @TODO
const initialState = [{ doors: [{ status: 'free' }] }, mockup];
const floors = handleAction(setRoom, (state, { payload }) => {
  return [{ doors: [{ status: payload.status }] }, mockup];
}, initialState);

export default combineReducers({
  notifications,
  floors,
});
