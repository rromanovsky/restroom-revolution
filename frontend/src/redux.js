import _ from 'lodash';
import { combineReducers } from 'redux';
import { createAction, handleAction } from 'redux-actions';
import { createSelector } from 'reselect';

// Actions
export const setRoom = createAction('ROOMS/SET');

// Selectors
export const getFloors = _.property('floors');

// Reducers
const initialState = [{
  doors: [{
    status: 'free',
  }],
}];
const floors = handleAction(setRoom, (state, { payload }) => {
  return [{ doors: [{ status: payload.status }] }];
}, initialState);

export default combineReducers({
  floors,
});
