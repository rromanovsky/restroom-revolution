import actionTypes from '../actions/types/app';

export default (state = {}, action) => {
  switch (action.type) {
    case actionTypes.GOT_DATA:
      return {
        ...state,
        data: action.data
      };

    default:
      return state;
  }
};
