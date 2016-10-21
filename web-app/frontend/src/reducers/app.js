import actionTypes from '../actions/types/app';

export default (state = {}, action) => {
  switch (action.type) {
    case actionTypes.GOT_DATA:
      return {
        ...state,
        data: action.data,
        error: false,
        loading: false
      };

    case actionTypes.LOADING_DATA:
      return {
        ...state,
        loading: true,
        error: false
      };

    case actionTypes.GOT_ERROR:
      return {
        ...state,
        error: action.err,
        loading: false
      };

    default:
      return state;
  }
};
